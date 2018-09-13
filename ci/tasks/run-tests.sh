#!/bin/bash

set -e

tar -zxvf bundled-deps/bundled-misthos-js-deps-*.tgz > /dev/null

if [[ $(diff -q deps/yarn.lock repo/yarn.lock) ]]; then
  echo "Deps are not up to date!"
  exit 1
fi

mv deps/node_modules repo/

pushd repo
make bsb-once

git log --pretty=format:'%h' -n 1 > gitref

if [[ "$(git status -s -uno)" != "" ]]; then
  echo "Compiler output differs from commited files"
  git --no-pager diff
  exit 1;
fi

make ci

popd

tar -zcvf "misthos-js-code-v$(cat code-version/number)-$(cat repo/gitref).tgz" repo > /dev/null

mv ./*.tgz bundled-code
