# PC Status - PC client

## Usage

```
pcstatus [type] [data]...
```

### types

- Notification

```pcstatus n [title] [message]```

- Progress

```pcstatus p [title] [message] [progress] <progress_max>```

- Task

```pcstatus t [title] [message] [task_status]```

Task Statuses:

ID | meaning
--- | ---
0 | CREATED
1 | STARTED
2 | RUNNING
3 | DONE




