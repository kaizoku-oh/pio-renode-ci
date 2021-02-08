#!/bin/bash -e

# Runs Robot Framework tests locally

RENODE_CHECKOUT=${RENODE_CHECKOUT:-~/code/renode}

pwd
ls -la
ls -la ../

${RENODE_CHECKOUT}/test.sh -t "${PWD}/../test/tests.yaml" --variable PWD_PATH:"${PWD}/.." -r "${PWD}/../test_results"