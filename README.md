# PC Status - PC client

PC Status – monitoring tool for processes running on pc

The consists of 3 subprograms:

- [PC Status API](https://github.com/pawelhanusik/PCStatus-api)

- [PC Status client-pc](https://github.com/pawelhanusik/PCStatus-client-pc)

- [PC Status client-android](https://github.com/pawelhanusik/PCStatus-client-android)

## Goal

The goal of the project is to add new feature to the smartphone by connecting it with pc. By doing so it will gain remote monitoring functionalities.

## Use cases

Progress of any bash script, any process, monitoring RAM, cpu usage & more.

---

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
