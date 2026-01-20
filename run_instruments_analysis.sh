codesign -s - -f --entitlements debug.entitlements ./build/app
xctrace record --template 'Leaks' --launch -- ./build/app