add_library(Solver backend.cpp abstractSolver.cpp startProfiles.cpp
    impl/ExplicitInFlowDirection.cpp
    impl/ExplicitAgainstFlowDirection.cpp
    impl/ImplicitAgainstFlowDirection.cpp
    impl/ImplicitInFlowDirection.cpp
    impl/Leapfrog.cpp)
target_link_libraries(Solver Configs)
