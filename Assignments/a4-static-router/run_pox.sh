set -e

cd py

# If no virtualenv exists, tell the user to run setup.sh first
if [ ! -d ".venv" ]; then
    echo "No virtualenv found. Please run setup.sh first."
    exit 1
fi

source .venv/bin/activate
python pox/pox.py sr_bridge