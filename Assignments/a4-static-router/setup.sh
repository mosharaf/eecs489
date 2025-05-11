set -e

echo "Generating Python proto files..."

cd cpp/proto || exit
./generate_python_proto.sh

cd ../../py
# If no virtualenv exists, create one
if [ ! -f ".venv/bin/activate" ]; then
    if [ -d ".venv" ]; then
        echo "Incomplete virtualenv found. Removing and recreating..."
        rm -rf .venv
    fi
    echo "No virtualenv found. Creating one..."
    python3 -m venv .venv
fi

source .venv/bin/activate

echo "Installing Python dependencies..."
sleep 1
pip install --upgrade -r requirements.txt