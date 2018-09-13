/* module WithFalleback = { */
/*   module ClientA = SmartbitClient; */
/*   module ClientB = BlockchainInfoClient; */
/*   let getUTXOs = addresses => */
/*     Belt.( */
/*       Js.Promise.( */
/*         ClientA.getUTXOs(addresses) */
/*         |> then_(utxos => */
/*              ClientB.getUTXOs(addresses) */
/*              |> then_(moreUtxos => Set.union(utxos, moreUtxos) |> resolve) */
/*              |> catch(_ => utxos |> resolve) */
/*            ) */
/*         |> catch(_ => ClientB.getUTXOs(addresses)) */
/*       ) */
/*     ); */
/* }; */
