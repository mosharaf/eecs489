# If protoc is not installed, tell the user to install it
if ! command -v protoc &> /dev/null
then
    echo "protoc could not be found. Please install Protocol Buffers first."
    exit 1
fi

protoc --python_out=. router_bridge.proto

mv router_bridge_pb2.py ../../py/pox/ext/