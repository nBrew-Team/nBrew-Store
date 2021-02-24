#include "config.hpp"
#include "lang.hpp"

#include <stdio.h>
#include <unistd.h>

extern std::unique_ptr<Config> config;
nlohmann::json appJson;

std::string Lang::get(const std::string &key) {
	if (!appJson.contains(key)) {
		return "MISSING: " + key;
	}

	return appJson.at(key).get_ref<const std::string&>();
}

std::string langs[] = {"en"};

void Lang::load(const std::string lang) {
	FILE* values;
	if (config->langPath() == 1) {
		// Check if exist.
		if (access("sdmc:/3ds/nBrew-Store/app.json", F_OK) == 0) {
			values = fopen(("sdmc:/3ds/nBrew-Store/app.json"), "rt");
			appJson = nlohmann::json::parse(values, nullptr, false);
			fclose(values);
			return;

		} else {
			values = fopen(("romfs:/lang/en/app.json"), "rt");
			appJson = nlohmann::json::parse(values, nullptr, false);
			fclose(values);
			return;
		}

	} else {
		// Check if exist.
		if (access(("romfs:/lang/" + lang + "/app.json").c_str(), F_OK) == 0) {
			values = fopen(std::string(("romfs:/lang/" + lang + "/app.json")).c_str(), "rt");
			appJson = nlohmann::json::parse(values, nullptr, false);
			fclose(values);
			return;

		} else {
			values = fopen(("romfs:/lang/en/app.json"), "rt");
			appJson = nlohmann::json::parse(values, nullptr, false);
			fclose(values);
			return;
		}
	}
}