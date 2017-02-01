import qbs

CppApplication {
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++11"
    files: [
        "main.cpp",
        "textmodel.cpp",
        "textmodel.h",
        "tokenizer.cpp",
        "tokenizer.h",
    ]

    Properties {
        condition: qbs.buildVariant === "debug"
        cpp.defines: ["PRINT_TABLE"]
    }

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
