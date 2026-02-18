# compiler/runner.py
import subprocess
import os

class CodeRunner:
    def __init__(self):
        # This acts as our engine to run real C, Java, and Python code
        pass

    def run_code(self, source_code, language):
        """Routes the code to the correct compiler/interpreter."""
        if language == "Python":
            return self._run_python(source_code)
        elif language == "C":
            return self._run_c(source_code)
        elif language == "Java":
            return self._run_java(source_code)
        else:
            return False, f"Unsupported language: {language}"

    def _run_python(self, code):
        # 1. Save code to a temporary file
        with open("temp_script.py", "w") as f:
            f.write(code)
        
        try:
            # 2. Run the file using the real Python interpreter
            # timeout=10 prevents infinite loops!
            result = subprocess.run(["python", "temp_script.py"], capture_output=True, text=True, timeout=10)
            
            # 3. Check if it succeeded or failed
            if result.returncode == 0:
                return True, result.stdout # Success: Return the output
            else:
                return False, result.stderr # Failed: Return the error message
        except subprocess.TimeoutExpired:
            return False, "Error: Execution timed out (Infinite Loop?)."
        except Exception as e:
            return False, str(e)

    def _run_c(self, code):
        with open("temp_code.c", "w") as f:
            f.write(code)
            
        try:
            # Phase 1: Compile the C code using GCC
            compile_res = subprocess.run(["gcc", "temp_code.c", "-o", "temp_exe"], capture_output=True, text=True)
            if compile_res.returncode != 0:
                return False, compile_res.stderr # Return Syntax/Compilation errors
            
            # Phase 2: Run the compiled .exe file
            exe_name = "temp_exe.exe" if os.name == 'nt' else "./temp_exe"
            run_res = subprocess.run([exe_name], capture_output=True, text=True, timeout=10)
            
            if run_res.returncode == 0:
                return True, run_res.stdout
            else:
                return False, run_res.stderr # Return Runtime errors (like division by zero)
        except subprocess.TimeoutExpired:
            return False, "Error: Execution timed out."
        except Exception as e:
            return False, f"Error (Is GCC installed?): {str(e)}"

    def _run_java(self, code):
        # Java needs the filename to match the public class name. We will enforce "Main".
        with open("Main.java", "w") as f:
            f.write(code)
            
        try:
            # Phase 1: Compile
            compile_res = subprocess.run(["javac", "Main.java"], capture_output=True, text=True)
            if compile_res.returncode != 0:
                return False, compile_res.stderr
            
            # Phase 2: Run
            run_res = subprocess.run(["java", "Main"], capture_output=True, text=True, timeout=10)
            
            if run_res.returncode == 0:
                return True, run_res.stdout
            else:
                return False, run_res.stderr
        except subprocess.TimeoutExpired:
            return False, "Error: Execution timed out."
        except Exception as e:
            return False, f"Error (Is Java JDK installed?): {str(e)}"