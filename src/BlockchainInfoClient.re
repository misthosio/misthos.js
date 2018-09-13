open Belt;

type config = {
  subdomain: string,
  network: Bitcoin.Networks.t,
};
let testnetConfig = {
  subdomain: "testnet.",
  network: Bitcoin.Networks.testnet,
};
let mainnetConfig = {subdomain: "", network: Bitcoin.Networks.bitcoin};

let float_ = Json.Decode.float;

let decodeUTXO = (config, raw) : Types.utxo =>
  Json.Decode.{
    txId: raw |> field("tx_hash_big_endian", string),
    txOutputN: raw |> field("tx_output_n", int),
    amount: raw |> field("value", float_) |> BTC.fromSatoshisFloat,
    confirmations: raw |> field("confirmations", int),
    address:
      raw
      |> field("script", string)
      |> Utils.bufFromHex
      |. Bitcoin.Address.fromOutputScript(config.network),
  };

let getUTXOs = (config, addresses) =>
  switch (addresses) {
  | [] => Js.Promise.resolve(Types.emptyUtxoSet)
  | addresses =>
    Js.Promise.(
      Fetch.fetch(
        "https://"
        ++ config.subdomain
        ++ "blockchain.info/unspent?format=json&active="
        ++ (
          addresses
          |. List.reduceU("", (. res, address) => res ++ "|" ++ address)
        )
        ++ "&cors=true",
      )
      |> then_(Fetch.Response.json)
      |> then_(raw =>
           raw
           |> Json.Decode.(
                field("unspent_outputs", array(decodeUTXO(config)))
              )
           |> Set.mergeMany(Types.emptyUtxoSet)
           |> resolve
         )
      |> catch(_err => Types.emptyUtxoSet |> resolve)
    )
  };
