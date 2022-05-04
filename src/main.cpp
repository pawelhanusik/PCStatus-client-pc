#include <iostream>
#include <cstdlib>

#include "config.h"
#include "Client.h"
#include "Sender.h"
#include "Logger.h"

#include "models/Model.h"
#include "models/Notification.h"
#include "models/Progress.h"
#include "models/Task.h"

using namespace std;

void printHelp(char *executableName) {
    printf("Usage: %s [type] [data]...\n", executableName);
    
    
    printf("Types:\n");
    
    printf("\t- Notification\n");
    printf("\t\t%s n [title] [message]\n", executableName);
    
    printf("\t- Progress\n");
    printf("\t\t%s p [title] [message] [progress] <progress_max>\n", executableName);
    printf("\t   update:\n");
    printf("\t\t%s p -u [id] [progress]\n", executableName);
    
    printf("\t- Task\n");
    printf("\t\t%s t [title] [message] [task_status]\n", executableName);
    printf("\t   update:\n");
    printf("\t\t%s t -u [id] [task_status]\n", executableName);

    printf("Task Statuses:\n");
    printf("\t ID | meaning\n");
    printf("\t -- | -------\n");
    printf("\t  0 | CREATED\n");
    printf("\t  1 | STARTED\n");
    printf("\t  2 | RUNNING\n");
    printf("\t  3 | DONE\n");

    exit(2);
}

enum Operation {
    CREATE,
    UPDATE
};
enum ModelType {
    UNKNOWN,
    NOTIFICATION,
    PROGRESS,
    TASK
};

ModelType getModelTypeFromArgs(int argc, char *argv[]) {
    if (argc < 2) {
        printHelp(argv[0]);
        return ModelType::UNKNOWN;
    }

    char *type = argv[1];
    
    if (type[0] == 'n') {
        return ModelType::NOTIFICATION;
    } else if (type[0] == 'p') {
        return ModelType::PROGRESS;
    } else if (type[0] == 't') {
        return ModelType::TASK;
    } else {
        return ModelType::UNKNOWN;
    }
}

Operation getOperationFromArgs(int argc, char *argv[]) {
    if (
        argc > 2
        && argv[2][0] == '-'
        && argv[2][1] == 'u'
    ) {
        return Operation::UPDATE;
    }

    return Operation::CREATE;
}

int main(int argc, char *argv[]) {
    ModelType type = getModelTypeFromArgs(argc, argv);
    Operation operation = getOperationFromArgs(argc, argv);

    if (type == ModelType::UNKNOWN) {
        printf("Unrecognized type.\n");
        printHelp(argv[0]);
        return 2;
    }
    
    CurlSender sender;
    Client client(sender);
    
    if (operation == Operation::CREATE) {
        Response response;

        if (type == ModelType::NOTIFICATION) {
            if (argc < 4) {
                printHelp(argv[0]);
                return 2;
            }
            
            Notification model;
            model.title = argv[2];
            model.message = argv[3];

            response = client.create(&model);
        } else if (type == ModelType::PROGRESS) {
            if (argc < 5) {
                printHelp(argv[0]);
                return 2;
            }
            
            Progress model;
            model.title = argv[2];
            model.message = argv[3];
            model.progress = atoi(argv[4]);
            if (argc >= 6) {
                model.progress_max = atoi(argv[5]);
            }

            response = client.create(&model);
        } else if (type == ModelType::TASK) {
            if (argc < 5) {
                printHelp(argv[0]);
                return 2;
            }
            
            Task model;
            model.title = argv[2];
            model.message = argv[3];
            model.status = (TaskStatus)atoi(argv[4]);

            response = client.create(&model);
        }

        if (response.success) {
            printf("%s\n", response.message.c_str());
        }
    } else if (operation == Operation::UPDATE) {
        if (type == ModelType::PROGRESS) {
            if (argc < 4) {
                printHelp(argv[0]);
                return 2;
            }
            
            Progress model;
            model.id = atoi(argv[3]);
            model.progress = atoi(argv[4]);

            client.update(&model);
        } else if (type == ModelType::TASK) {
            if (argc < 5) {
                printHelp(argv[0]);
                return 2;
            }
            
            Task model;
            model.id = atoi(argv[3]);
            model.status = (TaskStatus)atoi(argv[4]);

            client.update(&model);
        }
    }
    
    return 0;
}
