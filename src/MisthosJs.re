open Bitcoin;

let generateKeyPair = () => ECPair.makeRandom() |> ECPair.toWIF;

type ventureData = {
  ventureId: string,
  username: string,
  app: string,
};

type sharedData = {addresses: array(string)};

let encodeSharedData = data =>
  Json.Encode.(object_([("addresses", array(string, data.addresses))]));

let decodeSharedData = raw =>
  Json.Decode.{addresses: raw |> field("addresses", array(string))};

let readSharedData = ({ventureId, username, app}, keyPair) =>
  Js.Promise.(
    Blockstack.getFileFromUser(
      ventureId
      ++ "/"
      ++ Utils.storagePrefix(~appPubKey=Utils.publicKeyFromKeyPair(keyPair))
      ++ "/sharedData.json",
      ~username,
      ~app,
    )
    |> then_(nullFile =>
         switch (Js.Nullable.toOption(nullFile)) {
         | Some(file) =>
           Blockstack.decryptECIES(
             ~privateKey=keyPair |> Utils.privateKeyFromKeyPair,
             file |> Json.parseOrRaise,
           )
           |> Json.parseOrRaise
           |> decodeSharedData
           |. Some
           |> resolve

         | None => resolve(None)
         }
       )
  );
