{
    "targets": [
     {
        "target_name": "node-nbody",
        "include_dirs": [
            "include"
        ],
        "cflags": [
            "-std=c++11",
            "-fopenmp"
        ],
        "sources": ['<!@(ls -1 src/*.cc)' ]
     }]
}
