#!/bin/bash

PRIVATE_EXTENSION="private"
PUBLIC_EXTENSION="public"
DIR_NAME=".tokens"

WALLET_NAME="$1"
SMART_CONTRACT_NAME="$2"
PLAYER_ONE="$3"
PLAYER_TWO="$4"

mkdir -p ${DIR_NAME}

cleos wallet open
cleos wallet unlock --password $(cat ~/.wallet.pw)

cleos wallet create --name "${WALLET_NAME}" --file ".tokens/${WALLET_NAME}.pw"

generate_key_pair() {
  local base_filename="$1"
  echo "Creating key pair for ${base_filename}"

  # Execute the cleos create key command and save keys to files
  local key_output=$(cleos create key --to-console)
  local private_key=$(echo "$key_output" | awk '/Private key:/ {print $3}')
  local public_key=$(echo "$key_output" | awk '/Public key:/ {print $3}')

  # Save the keys to separate files
  echo "$private_key" > "${DIR_NAME}/${base_filename}.${PRIVATE_EXTENSION}"
  echo "$public_key" > "${DIR_NAME}/${base_filename}.${PUBLIC_EXTENSION}"
}

create_account() {
  echo "---"
  local account_name="$1"

  # Generate key pairs
  generate_key_pair "${account_name}"

  # Execute the cleos create account command
  echo "Creating account ${account_name}"
  cleos create account eosio "${account_name}" $(cat "${DIR_NAME}/${account_name}.${PUBLIC_EXTENSION}")

  # Execute the cleos import primary key command
  echo "Import key to the wallet ${WALLET_NAME}"
  cleos wallet import --name ${WALLET_NAME} --private-key $(cat "${DIR_NAME}/${account_name}.${PRIVATE_EXTENSION}")
}

create_account "${SMART_CONTRACT_NAME}"
create_account "${PLAYER_ONE}"
create_account "${PLAYER_TWO}"

