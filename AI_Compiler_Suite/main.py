# main.py
import json
import time
from compiler.lexer import Lexer
from compiler.parser import Parser
from ai_engine.fixer import AIFixer
from ai_engine.generator import CodeGenerator # <--- IMPORT THIS

def run_compiler_pipeline(source_code):
    print(f"\n📄 Processing Code:\n{source_code.strip()}")
    
    # 1. Try to compile
    try:
        print("🔹 Running Compiler...")
        lexer = Lexer(source_code)
        tokens = lexer.tokenize()
        parser = Parser(tokens)
        ast = parser.parse()
        print("\n✅ Success! AST Generated:")
        print(json.dumps(ast, indent=2))
        
    except Exception as e:
        print(f"\n❌ Error: {e}")
        print("⚠️ Engaging AI Self-Healing...")
        
        # 2. AI Auto-Fix
        fixer = AIFixer(use_mock=False)
        fixed_code = fixer.fix_code(source_code, str(e))
        print(f"\n✨ AI Suggested Fix:\n{fixed_code}")
        
        # 3. Retry
        print("🔄 Retrying...")
        run_compiler_pipeline(fixed_code) # Recursion to test the fix

# --- MAIN MENU ---
if __name__ == "__main__":
    print("========================================")
    print(" 🚀 AI-POWERED HYBRID COMPILER v1.0")
    print("========================================")
    print("1. Compile Source Code (Normal Mode)")
    print("2. Compile English Instructions (AI Mode)")
    
    choice = input("\nSelect Option (1 or 2): ")
    
    if choice == "1":
        # Test the Self-Healing
        broken_code = """
        var x = 10;
        print("Hello") 
        var y = 20;
        """
        run_compiler_pipeline(broken_code)
        
    elif choice == "2":
        # Test Natural Language Generation
        prompt = input("Enter instruction (e.g., 'Create a variable x with value 50'): ")
        
        # Call Generator
        generator = CodeGenerator(use_mock=False)
        generated_code = generator.generate_code(prompt)
        
        # Send generated code to compiler
        run_compiler_pipeline(generated_code)