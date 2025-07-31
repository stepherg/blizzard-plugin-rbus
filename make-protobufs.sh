#!/bin/sh

BLIZZARD_BASE="$HOME/projects/Blizzard"
OUT_DIR="protobuf"

mkdir $OUT_DIR &> /dev/null

protoc \
   --proto_path=/opt/homebrew/include \
   --c_out=$OUT_DIR \
   google/protobuf/any.proto \
   google/protobuf/empty.proto

protoc \
   --proto_path="$BLIZZARD_BASE/blizzard-plugin-description/proto" \
   --proto_path="$BLIZZARD_BASE/blizzard-descriptor/proto" \
   --proto_path="$BLIZZARD_BASE/blizzard-plugin-messages/proto" \
   --proto_path="$BLIZZARD_BASE/blizzard-value/proto" \
   --c_out=$OUT_DIR \
   messages.proto \
   description.proto \
   descriptor.proto \
   value.proto

