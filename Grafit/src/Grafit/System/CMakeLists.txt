#set(INCROOT ${PROJECT_SOURCE_DIR}/include/Grafit/System)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Grafit/System)

file(GLOB grafit_system_source_files
#    "${INCROOT}/Destructable.hpp"
#    "${INCROOT}/Clock.hpp"
    "${SRCROOT}/Clock.cpp"
#    "${INCROOT}/InputStream.hpp"
#    "${INCROOT}/Lock.hpp"
    "${SRCROOT}/Lock.cpp"
#    "${INCROOT}/Mutex.hpp"
    "${SRCROOT}/Mutex.cpp"
#    "${INCROOT}/NonCopyable.hpp"
#    "${INCROOT}/Sleep.hpp"
    "${SRCROOT}/Sleep.cpp"
#    "${INCROOT}/String.hpp"
#    "${INCROOT}/String.inl"
    "${SRCROOT}/String.cpp"
#    "${INCROOT}/Thread.hpp"
#    "${INCROOT}/Thread.inl"
    "${SRCROOT}/Thread.cpp"
#    "${INCROOT}/ThreadLocal.hpp"
#    "${INCROOT}/ThreadLocalPtr.hpp"
#    "${INCROOT}/ThreadLocalPtr.inl"
    "${SRCROOT}/ThreadLocal.cpp"
#    "${INCROOT}/Time.hpp"
    "${SRCROOT}/Time.cpp"
#    "${INCROOT}/Tipes.hpp"
#    "${INCROOT}/Utf.hpp"
#    "${INCROOT}/Utf.inl"
#    "${INCROOT}/Assert.hpp"
    "${SRCROOT}/Assert.cpp"
#    "${INCROOT}/SourceInfo.hpp"
#    "${INCROOT}/PlatformMacros.hpp"
#    "${INCROOT}/File.hpp"
    "${SRCROOT}/File.cpp"
    "${SRCROOT}/Path.cpp"
#    "${INCROOT}/FileStream.hpp"
    "${SRCROOT}/FileStream.cpp"
#    "${INCROOT}/SystemInfo.hpp"
    "${SRCROOT}/SystemInfo.cpp"
#    "${INCROOT}/Event.hpp"
#    "${INCROOT}/Signals/Slot.hpp"
#    "${INCROOT}/Signals/Slot.inl"
#    "${INCROOT}/Signals/Signal.hpp"
#    "${INCROOT}/Signals/Signal.inl"
#    "${INCROOT}/Signals/SlotMap.hpp"
#    "${INCROOT}/Signals/SlotMap.inl"
#    "${INCROOT}/Signals/Connection.hpp"
    "${SRCROOT}/Signals/Connection.cpp"
#    "${INCROOT}/Function.hpp"
#    "${INCROOT}/Factory.hpp"
#    "${INCROOT}/Uuid.hpp"
    "${SRCROOT}/Uuid.cpp"
#    "${INCROOT}/ResourceManager.hpp"
#    "${INCROOT}/ResourceManager.inl"
    "${SRCROOT}/ResourceManager.cpp"
    "${INCROOT}/Memory/smart_ptr.hpp"
    "${INCROOT}/Promise/AsyncBase.hpp"
    "${INCROOT}/Promise/AsyncBase.inl"
    "${INCROOT}/Promise/Promise.hpp"
    "${INCROOT}/Promise/Deferred.hpp"
    "${INCROOT}/Promise/EventLoop.hpp"
    "${SRCROOT}/Promise/EventLoop.cpp"
)

if(WIN32)
    set(grafit_system_extra_libs "-lwinmm")
    file(GLOB grafit_system_platform_source_files
        "${SRCROOT}/Win32/ClockImpl.hpp"
        "${SRCROOT}/Win32/ClockImpl.cpp"
        "${SRCROOT}/Win32/MutexImpl.hpp"
        "${SRCROOT}/Win32/MutexImpl.cpp"
        "${SRCROOT}/Win32/SleepImpl.hpp"
        "${SRCROOT}/Win32/SleepImpl.cpp"
        "${SRCROOT}/Win32/ThreadImpl.hpp"
        "${SRCROOT}/Win32/ThreadImpl.cpp"
        "${SRCROOT}/Win32/ThreadLocalImpl.hpp"
        "${SRCROOT}/Win32/ThreadLocalImpl.cpp"
        "${SRCROOT}/Win32/SystemInfoImpl.hpp"
        "${SRCROOT}/Win32/SystemInfoImpl.cpp"
        "${SRCROOT}/Win32/FileImpl.hpp"
        "${SRCROOT}/Win32/FileImpl.cpp"
    )
    source_group("Win32" FILES ${grafit_system_platform_source_files})
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    set(grafit_system_extra_libs ${COCOA_LIBRARY})
    file(GLOB grafit_system_platform_source_files
        "${SRCROOT}/Unix/ClockImpl.hpp"
        "${SRCROOT}/Unix/ClockImpl.cpp"
        "${SRCROOT}/Unix/MutexImpl.hpp"
        "${SRCROOT}/Unix/MutexImpl.cpp"
        "${SRCROOT}/Unix/SleepImpl.hpp"
        "${SRCROOT}/Unix/SleepImpl.cpp"
        "${SRCROOT}/Unix/ThreadImpl.hpp"
        "${SRCROOT}/Unix/ThreadImpl.cpp"
        "${SRCROOT}/Unix/ThreadLocalImpl.hpp"
        "${SRCROOT}/Unix/ThreadLocalImpl.cpp"
        "${SRCROOT}/OSX/SystemInfoImpl.hpp"
        "${SRCROOT}/OSX/SystemInfoImpl.mm"
    )
    source_group("OSX" FILES ${grafit_system_platform_source_files})
else()
    file(GLOB grafit_system_platform_source_files
        "${SRCROOT}/Unix/ClockImpl.hpp"
        "${SRCROOT}/Unix/ClockImpl.cpp"
        "${SRCROOT}/Unix/MutexImpl.hpp"
        "${SRCROOT}/Unix/MutexImpl.cpp"
        "${SRCROOT}/Unix/SleepImpl.hpp"
        "${SRCROOT}/Unix/SleepImpl.cpp"
        "${SRCROOT}/Unix/ThreadImpl.hpp"
        "${SRCROOT}/Unix/ThreadImpl.cpp"
        "${SRCROOT}/Unix/ThreadLocalImpl.hpp"
        "${SRCROOT}/Unix/ThreadLocalImpl.cpp"
        "${SRCROOT}/Unix/SystemInfoImpl.hpp"
        "${SRCROOT}/Unix/SystemInfoImpl.cpp"
        "${SRCROOT}/Unix/FileImpl.hpp"
        "${SRCROOT}/Unix/FileImpl.cpp"
    )
    source_group("Unix" FILES ${grafit_system_platform_source_files})
endif()

source_group("System" FILES ${grafit_system_source_files})

set(GRAPHIT_SYSTEM_LIBRARY grafit-system)
add_library(grafit-system SHARED ${grafit_system_source_files} ${grafit_system_platform_source_files})

target_link_libraries(grafit-system
#    boost_system-mt
#    boost_filesystem-mt
    ${grafit_system_extra_libs}
)

install(TARGETS ${GRAFIT_SYSTEM_LIBRARY}
    ARCHIVE DESTINATION lib COMPONENT lib
    LIBRARY DESTINATION lib COMPONENT lib)
