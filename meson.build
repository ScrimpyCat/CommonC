project('CommonC', 'c',
    default_options: ['c_std=gnu11']
)

add_global_arguments([
        '-Wno-logical-not-parentheses',
        '-Wno-missing-braces',
        '-Wno-multichar',
        '-Wno-unknown-pragmas',
    ],
    language: 'c'
)

src = [
    'CommonC/Allocator.c',
    'CommonC/Array.c',
    'CommonC/CCString.c',
    'CommonC/CollectionArray.c',
    'CommonC/Collection.c',
    'CommonC/CollectionFastArray.c',
    'CommonC/CollectionList.c',
    'CommonC/CommonC.c',
    'CommonC/ConcurrentBuffer.c',
    'CommonC/ConcurrentGarbageCollector.c',
    'CommonC/ConcurrentIDPool.c',
    'CommonC/ConcurrentIndexMap.c',
    'CommonC/ConcurrentQueue.c',
    'CommonC/CustomFormatSpecifiers.c',
    'CommonC/CustomInputFilters.c',
    'CommonC/Data.c',
    'CommonC/DataBuffer.c',
    'CommonC/DebugAllocator.c',
    'CommonC/DebugTypes.c',
    'CommonC/Dictionary.c',
    'CommonC/DictionaryHashMap.c',
    'CommonC/EpochGarbageCollector.c',
    'CommonC/File.c',
    'CommonC/FileHandle.c',
    'CommonC/FileSystem.c',
    'CommonC/Hash.c',
    'CommonC/HashMap.c',
    'CommonC/HashMapSeparateChainingArray.c',
    'CommonC/HashMapSeparateChainingArrayDataOrientedAll.c',
    'CommonC/HashMapSeparateChainingArrayDataOrientedHash.c',
    'CommonC/LazyGarbageCollector.c',
    'CommonC/LinkedList.c',
    'CommonC/Logging.c',
    'CommonC/MemoryAllocation.c',
    'CommonC/OrderedCollection.c',
    'CommonC/Path.c',
    'CommonC/PathComponent.c',
    'CommonC/ProcessInfo.c',
    'CommonC/Queue.c',
    'CommonC/SystemInfo.c',
    'CommonC/Task.c',
    'CommonC/TaskQueue.c',
    'CommonC/TypeCallbacks.c',
]

deps = []

if host_machine.system() == 'darwin'
    add_languages('objc')
    src += [
        'CommonC/CFAllocator.c',
        'CommonC/SystemPath.m',
    ]
    deps += [dependency('Foundation')]
endif

library('CommonC', src,
    include_directories: include_directories('CommonC'),
    dependencies: deps
)
