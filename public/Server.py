from flask import Flask, jsonify
from flask_cors import CORS  # Import CORS
import subprocess

app = Flask(__name__)
CORS(app)  # Enable CORS for all routes

@app.route('/geturls')
def get_urls():
    try:
        result = subprocess.run(
            ["C:\\Users\\bengs\\OneDrive\\Desktop\\WikiWander\\x64\\Debug\\wiki_API_test.exe"],
            capture_output=True, text=True, encoding='utf-8', errors='ignore'
        )
        if result.returncode != 0:
            print("Error running executable:", result.stderr)
            raise Exception("Subprocess returned non-zero exit status.")

        output = result.stdout.splitlines()
        start_url = output[0] if len(output) > 0 else ""
        end_url = output[1] if len(output) > 1 else ""
        # setVals = output[2:]
        # print("Set Value:", setVals)

        return jsonify(start=start_url, end=end_url)
    except Exception as e:
        return jsonify(error=str(e)), 500

if __name__ == '__main__':
    app.run(port=5000)
