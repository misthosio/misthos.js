let bufToHex = buf => buf |. BufferExt.toStringWithEncoding("hex");
let bufFromHex = BufferExt.fromStringWithEncoding(~encoding="hex");

let publicKeyFromKeyPair = pair =>
  Bitcoin.(pair |> ECPair.getPublicKey |> bufToHex);
let privateKeyFromKeyPair = pair =>
  Bitcoin.(pair |> ECPair.getPrivateKey |> bufToHex);

let storagePrefix = (~appPubKey) =>
  appPubKey
  |> bufFromHex
  |. Bitcoin.ECPair.fromPublicKey({"network": Bitcoin.Networks.bitcoin})
  |> Bitcoin.Address.fromKeyPair;
