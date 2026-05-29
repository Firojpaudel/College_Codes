import sys
import importlib

def test_python_version():
    """Ensure Python version is 3.7 or higher."""
    assert sys.version_info >= (3, 7), "Python version must be 3.7 or higher"

def test_required_packages():
    """Test if all required packages for DWDM labs are installed correctly."""
    required_packages = [
        'pandas', 
        'numpy', 
        'matplotlib', 
        'sklearn', 
        'mlxtend', 
        'streamlit', 
        'openpyxl',
        'pytest'
    ]
    
    missing_packages = []
    
    for package in required_packages:
        try:
            importlib.import_module(package)
        except ImportError:
            missing_packages.append(package)
            
    assert not missing_packages, f"Missing required packages: {', '.join(missing_packages)}"

def test_virtual_environment():
    """Check if the test is running inside a Python virtual environment."""
    is_venv = (hasattr(sys, 'real_prefix') or 
               (hasattr(sys, 'base_prefix') and sys.base_prefix != sys.prefix))
    
    assert is_venv, "PyTest is not running inside a virtual environment! Please activate '.venv' first."
