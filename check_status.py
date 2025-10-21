#!/usr/bin/env python3

import requests
import json
import sys

def check_submission_status(submission_id, token):
    url = f"https://acm.sjtu.edu.cn/OnlineJudge/api/v1/submission/{submission_id}"

    headers = {
        "Authorization": f"Bearer {token}",
    }

    try:
        response = requests.get(url, headers=headers, timeout=10)
        response.raise_for_status()
        return response.json()
    except Exception as e:
        print(f"Error checking status: {e}")
        return None

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 check_status.py <submission_id> <token>")
        sys.exit(1)

    submission_id = sys.argv[1]
    token = sys.argv[2]

    result = check_submission_status(submission_id, token)

    if result:
        print(json.dumps(result, indent=2))
    else:
        print("Status check failed")
        sys.exit(1)