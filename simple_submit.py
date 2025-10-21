#!/usr/bin/env python3

import requests
import json
import sys

def submit_to_acmoj(problem_id, code_file, token):
    url = f"https://acm.sjtu.edu.cn/OnlineJudge/api/v1/problem/{problem_id}/submit"

    headers = {
        "Authorization": f"Bearer {token}",
        "Content-Type": "application/x-www-form-urlencoded"
    }

    try:
        with open(code_file, 'r') as f:
            code_text = f.read()
    except Exception as e:
        print(f"Error reading file: {e}")
        return None

    data = {
        "language": "cpp",
        "code": code_text
    }

    try:
        response = requests.post(url, headers=headers, data=data, timeout=10)
        response.raise_for_status()
        return response.json()
    except Exception as e:
        print(f"Error submitting: {e}")
        return None

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python3 simple_submit.py <problem_id> <code_file> <token>")
        sys.exit(1)

    problem_id = sys.argv[1]
    code_file = sys.argv[2]
    token = sys.argv[3]

    result = submit_to_acmoj(problem_id, code_file, token)

    if result:
        print(json.dumps(result, indent=2))
    else:
        print("Submission failed")
        sys.exit(1)