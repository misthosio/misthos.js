type authRequest;
[@bs.module "blockstack"]
external makeAuthRequest :
  (
    ~transitKey: string,
    ~redirectURI: string,
    ~manifestURI: string,
    ~scopes: array(string),
    ~appDomain: string
  ) =>
  authRequest =
  "";

[@bs.module "blockstack"]
external redirectToSignInWithAuthRequest : authRequest => unit = "";

[@bs.module "blockstack"]
external redirectToSignIn :
  (~redirectURI: string, ~manifestURI: string, ~scopes: array(string)) => unit =
  "";

[@bs.module "blockstack"] external signUserOut : unit => unit = "";

[@bs.module "blockstack"]
external handlePendingSignIn : unit => Js.Promise.t(userData) = "";

[@bs.module "blockstack"]
external getFileDecrypted : string => Js.Promise.t(Js.nullable(string)) =
  "getFile";

[@bs.module "blockstack"]
external getFileNotDecrypted :
  (string, [@bs.as {json| {"decrypt": false} |json}] _) =>
  Js.Promise.t(Js.nullable(string)) =
  "getFile";

[@bs.module "blockstack"]
external getFileWithJsOpts :
  (string, Js.t({..})) => Js.Promise.t(Js.nullable(string)) =
  "getFile";

let getFileFromUser = (file, ~username, ~app) =>
  getFileWithJsOpts(
    file,
    {"username": username, "decrypt": false, "app": app},
  );

let getFileFromUserAndDecrypt = (file, ~username) =>
  getFileWithJsOpts(file, {"username": username, "decrypt": true});

[@bs.module "blockstack"]
external putFileEncrypted : (string, string) => Js.Promise.t(unit) =
  "putFile";

[@bs.module "blockstack"]
external _putFileEncryptedFor :
  (string, string, {. "encrypt": string}) => Js.Promise.t(unit) =
  "putFile";

let putFileEncryptedFor = (~path, ~content, ~pubKey) =>
  _putFileEncryptedFor(path, content, {"encrypt": pubKey});

[@bs.module "blockstack"]
external putFileNotEncrypted :
  (string, string, [@bs.as {json| {"encrypt": false} |json}] _) =>
  Js.Promise.t(unit) =
  "putFile";

[@bs.module "blockstack"]
external getUserAppFileUrl :
  (~path: string, ~username: string, ~appOrigin: string) =>
  Js.Promise.t(string) =
  "";

[@bs.module "blockstack/lib/keys.js"]
external makeECPrivateKey : unit => string = "";

type profile;
[@bs.module "blockstack"]
external lookupProfile : string => Js.Promise.t(profile) = "";

[@bs.module "blockstack/lib/encryption.js"]
external encryptECIES : (~publicKey: string, string) => Js.Json.t = "";
[@bs.module "blockstack/lib/encryption.js"]
external decryptECIES : (~privateKey: string, Js.Json.t) => string = "";
