//
// Created by stephen on 08/01/24.
//

#include "../include/BluetoothLE.h"

class BluetoothLE;

std::string BluetoothLE::capabilities() const {
    switch (_capabilities) {
        case DisplayOnly:
            return "DisplayOnly";
        case DisplayYesNo:
            return "DisplayYesNo";
        case KeyboardOnly:
            return "KeyboardOnly";
        case NoInputNoOutput:
            return "NoInputNoOutput";
        case KeyboardDisplay:
            return "KeyboardDisplay";
        default:
            return "";
    }
}

void BluetoothLE::set_capabilities(BluetoothLE::Capabilities capabilities) { _capabilities = capabilities; }

std::shared_ptr<BluetoothLE> BluetoothLE::get_agent() { return std::dynamic_pointer_cast<BluetoothLE>(path_get("/agent")); }

std::shared_ptr<BluetoothLE> BluetoothLE::path_get(const std::string& path) {
    std::scoped_lock lock(_child_access_mutex);
    if (!path_exists(path)) {
        //throw Exception::PathNotFoundException(_path, path);
        std::cout << "Path Not Found Error" << std::endl;
    }
    return _children[path];
}

bool BluetoothLE::path_exists(const std::string& path) {
    std::scoped_lock lock(_child_access_mutex);
    return _children.find(path) != _children.end();
}

void BluetoothLE::init() {
    _conn->init();

    // Load all managed objects
    BluetoothLE::Holder managed_objects = object_manager()->GetManagedObjects();
    for (auto& [path, managed_interfaces] : managed_objects.get_dict_object_path()) {
        path_add(path, managed_interfaces);
    }

    _conn->add_match("type='signal',sender='org.bluez'");

    // Create the agent that will handle pairing.
    _agent = std::make_shared<BluetoothLE>(_conn, "org.bluez", "/agent");
    path_append_child("/agent", std::static_pointer_cast<BluetoothLE>(_agent));
}