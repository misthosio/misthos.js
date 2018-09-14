// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Jest = require("@glennsl/bs-jest/src/jest.js");
var MisthosJs = require("../src/MisthosJs.bs.js");
var BitcoinjsLib = require("bitcoinjs-lib");

var key = BitcoinjsLib.ECPair.fromWIF("L4mq6KSmWo6VAoMzDvVuSEG5sqWw2CPujQjeHQYWHnzr89CFKHzs");

Jest.testPromise("Can read sharedData from venture", undefined, (function () {
        return MisthosJs.readSharedData(/* record */[
                      /* ventureId */"a78d4641-b587-4984-a88e-10c57539cd5d",
                      /* username */"misthosio.id",
                      /* app */"https://localhost:3000"
                    ], key).then((function (data) {
                      return Promise.resolve(Jest.Expect[/* toEqual */12](/* record */[/* addresses : array */[
                                        "2NDJX3aDfNxjJLaFEeRBUfa3pV6LSD8G6Re",
                                        "2Mt34Uak51oWUKCL9AC87Ddn8BCdNTPm9Es"
                                      ]], Jest.Expect[/* expect */0](data)));
                    }));
      }));

exports.key = key;
/* key Not a pure module */
