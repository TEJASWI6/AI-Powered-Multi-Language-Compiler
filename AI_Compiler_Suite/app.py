import streamlit as st
from compiler.runner import CodeRunner
from ai_engine.fixer import AIFixer
from ai_engine.generator import CodeGenerator
from ai_engine.analyzer import ComplexityAnalyzer

# --- PAGE CONFIGURATION ---
st.set_page_config(page_title="Multi-Language AI Compiler", page_icon="⚡", layout="wide")

# Initialize Session State memory
if "fixed_code" not in st.session_state:
    st.session_state.fixed_code = None
if "complexity_result" not in st.session_state:
    st.session_state.complexity_result = None

st.title("⚡ Multi-Language AI Compiler Suite")
st.markdown("### *Compile C, Java, and Python with AI Auto-Correction & Analysis*")

# --- SIDEBAR (Settings & AI Features) ---
with st.sidebar:
    st.header("⚙️ Settings")
    language = st.selectbox("Select Language", ["Python", "C", "Java"])
    mode = st.radio("Input Mode", ["Code Editor", "Natural Language (AI)"])
    
    st.divider()
    st.header("✨ AI Features")
    # THE NEW EDUCATIONAL TOGGLE
    edu_mode = st.checkbox("🎓 Educational Mode", value=False, help="AI will add comments explaining the code line-by-line.")

code_input = ""

# --- INPUT AREA ---
if mode == "Natural Language (AI)":
    prompt = st.text_area("💬 Enter English Instructions:", height=100, 
                          placeholder=f"E.g., Write a {language} program to print prime numbers from 1 to 100")
    if st.button("✨ Generate Code"):
        with st.spinner(f"🤖 AI is writing {language} code..."):
            gen = CodeGenerator(use_mock=False)
            # Pass the edu_mode flag to the generator
            code_input = gen.generate_code(prompt, language, edu_mode)
            
            # Reset memory on new generation
            st.session_state.fixed_code = None 
            st.session_state.complexity_result = None
else:
    # Default code with a nested loop (Perfect for testing the Big-O Analyzer!)
    default_code = ""
    if language == "Python":
        default_code = "print('Hello World')\nfor i in range(10):\n    for j in range(10):\n        print(i * j)"
    elif language == "C":
        default_code = '#include <stdio.h>\nint main() {\n    int i, j;\n    for(i=0; i<10; i++) {\n        for(j=0; j<10; j++) {\n            printf(\"%d\", i*j);\n        }\n    }\n    return 0\n}'
    elif language == "Java":
        default_code = 'public class Main {\n    public static void main(String[] args) {\n        for(int i=0; i<10; i++) {\n            for(int j=0; j<10; j++) {\n                System.out.println(i*j);\n            }\n        }\n    }\n}'
    
    code_input = st.text_area(f"📝 Write {language} Code:", height=250, value=default_code)

if code_input:
    st.subheader(f"💻 Source Code ({language})")
    st.code(code_input, language=language.lower())

st.divider()

# --- ACTION BUTTONS (Side by Side) ---
col_run, col_analyze = st.columns([1, 1])

with col_run:
    run_pressed = st.button("🚀 Compile & Run", use_container_width=True)
with col_analyze:
    # THE NEW ANALYZER BUTTON
    analyze_pressed = st.button("⏱️ Analyze Time/Space Complexity", use_container_width=True)

# --- 1. COMPLEXITY ANALYZER LOGIC ---
if analyze_pressed and code_input:
    st.session_state.fixed_code = None # Hide previous fixes
    with st.spinner("🧠 Calculating Big-O Bounds..."):
        analyzer = ComplexityAnalyzer()
        st.session_state.complexity_result = analyzer.analyze(code_input, language)
        
if st.session_state.complexity_result:
    st.subheader("📊 Algorithmic Complexity")
    st.info(st.session_state.complexity_result)

# --- 2. EXECUTION & FIXER LOGIC ---
if run_pressed and code_input:
    st.session_state.fixed_code = None 
    st.session_state.complexity_result = None
    st.subheader("⚙️ Execution Output")
    
    runner = CodeRunner()
    with st.spinner(f"Running {language} compiler..."):
        success, output = runner.run_code(code_input, language)
    
    if success:
        st.success("✅ Execution Successful!")
        st.code(output)
    else:
        st.error(f"❌ Error Detected:\n{output}")
        
        st.warning("⚠️ Engaging AI Auto-Fixer...")
        with st.spinner("💊 AI is analyzing and rewriting code..."):
            fixer = AIFixer(use_mock=False)
            # Pass the edu_mode flag so the AI explains the fix!
            st.session_state.fixed_code = fixer.fix_code(code_input, output, language, edu_mode)

# --- 3. VERIFICATION UI ---
if st.session_state.fixed_code:
    st.markdown("---")
    st.subheader("✨ AI Corrected Code")
    if edu_mode:
        st.caption("🎓 Educational Mode: The AI has added comments to explain the fix.")
    st.code(st.session_state.fixed_code, language=language.lower())
    
    if st.button("✅ Verify & Run Fixed Code"):
        st.subheader("🔄 Verification Output")
        runner = CodeRunner()
        with st.spinner(f"Verifying fixed {language} code..."):
            success_2, output_2 = runner.run_code(st.session_state.fixed_code, language)
        
        if success_2:
            st.success("🎉 Fix Verified! Execution Successful!")
            st.code(output_2)
        else:
            st.error(f"❌ AI Fix Failed to resolve the issue:\n{output_2}")