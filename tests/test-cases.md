# Manual test cases

| ID | Action | Expected result |
|---|---|---|
| T01 | Open dashboard on a fresh run | 0 missions, 500 CU, 3 explorers |
| T02 | Create mission with 50 CU | Mission is Planned; reserve falls to 450 CU |
| T03 | Launch a planned Historian mission | Status changes to Completed; action is shown |
| T04 | Submit energy 10 CU | Request rejected with validation message |
| T05 | Submit energy 250 CU | Request rejected with validation message |
| T06 | Submit a mission with empty name | Request rejected with validation message |
| T07 | Launch same mission a second time | Request rejected as already launched |
| T08 | Reload browser while server is running | Mission data remains available |
| T09 | Restart server | Data resets because storage is in memory |
