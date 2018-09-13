type config = {subdomain: string};

let testnetConfig = {subdomain: "testnet-api"};

let mainnetConfig = {subdomain: "api"};

let float_ = Json.Decode.float;

let decodeUTXO = raw : Types.utxo =>
  Json.Decode.{
    txId: raw |> field("txid", string),
    txOutputN: raw |> field("n", int),
    amount: raw |> field("value_int", float_) |> BTC.fromSatoshisFloat,
    confirmations: raw |> field("confirmations", int),
    address: field("addresses", array(string), raw)[0],
  };

let decodeUTXOs = raw =>
  Json.Decode.(
    raw
    |> withDefault([], field("unspent", withDefault([], list(decodeUTXO))))
  );

let decodeNextLink = raw =>
  Json.Decode.(
    raw |> optional(field("paging", field("next_link", string)))
  );

let rec fetchAll = (link, decoder, collector) =>
  Js.Promise.(
    switch (link) {
    | Some(link) =>
      Fetch.fetch(link)
      |> then_(Fetch.Response.json)
      |> then_(res =>
           fetchAll(
             decodeNextLink(res),
             decoder,
             collector |> List.append(decoder(res)),
           )
         )
    | None => resolve(collector)
    }
  );

let getUTXOs = (config, addresses) =>
  switch (addresses) {
  | [] => Js.Promise.resolve(Types.emptyUtxoSet)
  | addresses =>
    fetchAll(
      Some(
        "https://"
        ++ config.subdomain
        ++ ".smartbit.com.au/v1/blockchain/address/"
        ++ List.fold_left((res, a) => a ++ "," ++ res, "", addresses)
        ++ "/unspent?limit=1000",
      ),
      decodeUTXOs,
      [],
    )
    |> Js.Promise.then_(utxos =>
         utxos
         |. Belt.List.toArray
         |> Belt.Set.mergeMany(Types.emptyUtxoSet)
         |> Js.Promise.resolve
       )
  };
