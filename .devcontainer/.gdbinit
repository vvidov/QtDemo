python
import sys
sys.path.insert(0, '/home/vscode/.gdb/qt6')
import qt6printers
qt6printers.register_printers(None)
end

set print pretty on
set print object on
set print static-members on
set print vtbl on
set print demangle on
set demangle-style gnu-v3
set print array on
set print array-indexes on

# Qt6 specific settings
set print repeats 0
set print elements 1000
