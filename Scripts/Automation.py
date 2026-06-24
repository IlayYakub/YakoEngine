import argparse
import shutil
import subprocess
import sys
from pathlib import Path
from enum import Enum


class Paths:
        scripts_dir = Path(__file__).parent
        root_dir= scripts_dir.parent
        build_dir = root_dir / "Build"
        toolchain_file = build_dir / "conan_toolchain.cmake"


class ArgumentParser:
    def __init__(self):
        self.parser = argparse.ArgumentParser()

        # Arguments that can be parsed
        self.parser.add_argument("--format_all", action="store_true", help="Format files based on .clang-format")
        self.parser.add_argument("--WIN64", action="store_true", help="Used arch is WIN64")
        self.parser.add_argument("--VS2022", action="store_true", help="Used IDE is Visual Studio 17 2022")
        self.parser.add_argument("--config", choices = ["debug", "release"], default="debug", help="Used configuration for generation/build")
        self.parser.add_argument("--gen_build", action="store_true", help="Performs generation stage")

    def Parse(self):
        self.args = self.parser.parse_args()

    def GetArgs(self):
        return self.args


class ArgsHandler:
    def __init__(self):
        pass

    def Handle(self, args):
        self.args = args

        if(self.args.format_all):
            self.RunFormatting()

        if(self.args.gen_build):
            self.RunGenerationAndBuildStages()

    def RunFormatting(self):
        dirs_to_format = [
            Paths.root_dir / "YakoEngine",
            Paths.root_dir / "YakoEngineTester", 
            Paths.root_dir / "SandBox", 
            Paths.root_dir / "Games"
        ]

        extensions_to_format = [
            ".h",
            ".hpp",
            ".cpp"
        ]

        print("[INFO] Run formatting...")
        for dir_to_format in dirs_to_format:
            if(dir_to_format.exists()):
                for file_path in dir_to_format.rglob("*"):
                    if(file_path.is_file() and file_path.suffix in extensions_to_format):
                        res = subprocess.run(["clang-format", "-i", str(file_path)])
                        if(res.returncode != 0):
                            print(f"[WARNING] Something went wrong during formatting file: {file_path}!")
            else:
                print(f"[WARNING] Dir to format doesn't exist: {dir_to_format}!")
        print("[INFO] Formatting ompleted successfully!")
            

    def RunGenerationAndBuildStages(self):
        Paths.build_dir.mkdir(exist_ok = True)

        # Choose generator
        generator = "Visual Studio 17 2022" # default generator
        if(self.args.VS2022):
            generator = "Visual Studio 17 2022"

        # Choose architecture
        architecture = "x64" # default architecture
        if(self.args.WIN64):
            architecture = "x64"

        # CMake configuration
        cmake_generation_command = [
            "cmake", "..",
            "-S", str(Paths.root_dir),
            "-B", str(Paths.build_dir),
            "-G", generator,
            "-A", architecture,
            f"-DCMAKE_TOOLCHAIN_FILE={Paths.toolchain_file}"
        ]

        res = subprocess.run(cmake_generation_command, cwd = Paths.build_dir)
        if(res.returncode != 0):
            print("[ERROR] CMake generation failed!")
            sys.exit(1)
        print("[INFO] CMake configuration completed successfully!")

        # CMake build
        cmake_build_cmd = [
            "cmake",
            "--build", str(Paths.build_dir),
            "--config", self.args.config
        ]

        res = subprocess.run(cmake_build_cmd)
        if res.returncode != 0:
            print("[ERROR] CMake build failed!")
            sys.exit(1)
        print("[INFO] CMake build completed successfully!")

# Entry point
def main():
    paths = Paths()

    argument_parser = ArgumentParser()
    argument_parser.Parse()
    args = argument_parser.GetArgs()

    args_handler = ArgsHandler()
    args_handler.Handle(args)

if __name__ == "__main__":
    main()


# Automation.py --format_all --WIN64 --VS2022 -- config Debug --Generate --Build