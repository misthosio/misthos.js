#!/bin/bash

set -eu
set -x

if [[ -z ${VERSION_FROM} ]]; then
  echo >&2 "VERSION_FROM environment variable not set, or empty.  Did you misconfigure Concourse?"
  exit 2
fi
if [[ ! -f ${VERSION_FROM} ]]; then
  echo >&2 "Version file (${VERSION_FROM}) not found.  Did you misconfigure Concourse?"
  exit 2
fi
export VERSION=$(cat ${VERSION_FROM})
if [[ -z ${VERSION} ]]; then
  echo >&2 "Version file (${VERSION_FROM}) was empty.  Did you misconfigure Concourse?"
  exit 2
fi

if [[ ! -f ${REPO_ROOT}/ci/release_notes.md ]]; then
  echo >&2 "ci/release_notes.md not found.  Did you forget to write them?"
  exit 1
fi

# GIT!
if [[ -z $(git config --global user.email) ]]; then
        git config --global user.email "bot@misthos.io"
fi
if [[ -z $(git config --global user.name) ]]; then
        git config --global user.name "CI Bot"
fi

###############################################################

pushd ${REPO_ROOT}
set +x
echo 'Populating .npmrc'
cat > ./.npmrc <<EOF
//registry.npmjs.org/:_authToken=${NPM_TOKEN}
EOF
set -x

yarn publish --new-version ${VERSION}
popd

echo "v${VERSION}"                         > ${RELEASE_ROOT}/tag
echo "${RELEASE_NAME} v${VERSION}"         > ${RELEASE_ROOT}/name
mv ${REPO_ROOT}/ci/release_notes.md          ${RELEASE_ROOT}/notes.md

# so that future steps in the pipeline can push our changes
cp -a ${REPO_ROOT} ${REPO_OUT}/git

