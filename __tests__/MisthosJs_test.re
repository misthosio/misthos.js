open Jest;
open Expect;

open Bitcoin;
let key =
  ECPair.fromWIF("L4mq6KSmWo6VAoMzDvVuSEG5sqWw2CPujQjeHQYWHnzr89CFKHzs");

let () =
  testPromise("Can read sharedData", () =>
    Js.Promise.(
      key
      |> MisthosJs.readSharedData({
           ventureId: "a78d4641-b587-4984-a88e-10c57539cd5d",
           username: "misthosio.id",
           app: "https://localhost:3000",
         })
      |> then_(data =>
           expect(data)
           |> toEqual(
                Some(
                  {
                    addresses: [|
                      "2NDJX3aDfNxjJLaFEeRBUfa3pV6LSD8G6Re",
                      "2Mt34Uak51oWUKCL9AC87Ddn8BCdNTPm9Es",
                    |],
                  }: MisthosJs.sharedData,
                ),
              )
           |> resolve
         )
    )
  );
