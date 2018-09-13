type utxo = {
  txId: string,
  txOutputN: int,
  address: string,
  amount: BTC.t,
  confirmations: int,
};
module UtxoCmp = {
  let compareUtxos =
    (.
      {txId: id1, txOutputN: out1}: utxo,
      {txId: id2, txOutputN: out2}: utxo,
    ) => {
      let c = compare(id1, id2);
      if (c != 0) {
        c;
      } else {
        compare(out1, out2);
      };
    };
  include Belt.Id.MakeComparableU({
    type t = utxo;
    let cmp = compareUtxos;
  });
};
type utxoSet = Belt.Set.t(UtxoCmp.t, UtxoCmp.identity);
let emptyUtxoSet = Belt.Set.make(~id=(module UtxoCmp));
