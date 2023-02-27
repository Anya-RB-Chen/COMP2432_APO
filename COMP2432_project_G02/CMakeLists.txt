cmake_minimum_required(VERSION 3.21)
project(COMP2432_project_G02 C)

set(CMAKE_C_STANDARD 99)

add_executable(COMP2432_project_G02 main.c classes/time_type.h classes/time_type.c classes/vector.h classes/vector.c classes/appointment.h userProcess.c main.h protocol/coding_tools.c protocol/coding_tools.h classes/scheduling.c classes/scheduling.h protocol/appointment_notification_protocol.c protocol/appointment_notification_protocol.h modules/modules.h modules/appointment_module.c modules/schedule_module.c protocol/prototype_of_pipe_usage.c protocol/schedule_requiring_protocol.c protocol/schedule_requiring_protocol.h modules/output_module.c modules/output_module.h classes/appointment.c tools.c tools.h)
