#include <iostream>
#include <cstdlib>

#include "config.h"
#include "Client.h"
#include "Logger.h"

#include "models/Model.h"
#include "models/Notification.h"
#include "models/Progress.h"
#include "models/Task.h"

using namespace std;

void printHelp() {
    printf("Help is not written yet...\n");
    exit(2);
}


enum ModelType {
    UNKNOWN,
    NOTIFICATION,
    PROGRESS,
    TASK
};

ModelType getModelTypeFromArgs(int argc, char *argv[]) {
    if (argc < 2) {
        printHelp();
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

int main(int argc, char *argv[]) {
    ModelType type = getModelTypeFromArgs(argc, argv);

    if (type == ModelType::UNKNOWN) {
        printf("Unrecognized type.\n");
        printHelp();
        return 2;
    }
    
    CurlSender sender;
    Client client(sender);
    
    if (type == ModelType::NOTIFICATION) {
        if (argc < 4) {
            printHelp();
            return 2;
        }
        
        Notification model;
        model.title = argv[2];
        model.message = argv[3];

        client.create(&model);
    } else if (type == ModelType::PROGRESS) {
        if (argc < 5) {
            printHelp();
            return 2;
        }
        
        Progress model;
        model.title = argv[2];
        model.message = argv[3];
        model.progress = atoi(argv[4]);
        if (argc >= 6) {
            model.progress_max = atoi(argv[5]);
        }

        client.create(&model);
    } else if (type == ModelType::TASK) {
        if (argc < 5) {
            printHelp();
            return 2;
        }
        
        Task model;
        model.title = argv[2];
        model.message = argv[3];
        model.status = (TaskStatus)atoi(argv[4]);

        client.create(&model);
    }
    
    return 0;
}
