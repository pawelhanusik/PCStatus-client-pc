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
Update  
```pcstatus p -u [id] [progress]```

- Task  
```pcstatus t [title] [message] [task_status]```  
Update  
```pcstatus t -u [id] [task_status]```

Task Statuses:

 ID | meaning
----|---------
  0 | CREATED
  1 | STARTED
  2 | RUNNING
  3 | DONE

## Config

Configuration is done before compilation!

Please edit `config.h` file to configure the program.

## Compiling

1. Make sure to have libcurl installed

1. Run

    `make`
