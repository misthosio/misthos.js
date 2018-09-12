open Bitcoin;

let generateKeyPair = () => ECPair.makeRandom() |> ECPair.toWIF;

type sharedData = {addresses: array(string)};

let encodeSharedData = data =>
  Json.Encode.(object_([("addresses", array(string, data.addresses))]));
