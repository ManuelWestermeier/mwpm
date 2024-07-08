#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

using namespace std;

template<class T>
void print(T out) {
	cout << out << endl;
}

int rmDir(string dir) {
	try {
		// Check if the directory exists
		if (fs::exists(dir)) {
			// Remove the directory and all its contents
			fs::remove_all(dir);
			return 0;
		}
		else {
			std::cout << "Directory does not exist." << std::endl;
			return 1;
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Error removing directory: " << e.what() << std::endl;
		return 1;
	}
}

void help() {
	print("usage:");
	print("mwpm {folder} {command} {...}");
	print("mwpm {folder} {install | i} {repo}@{githubUser}");
	print("mwpm {folder} {update | u} {repo}@{githubUser}");
	print("mwpm {folder} {remove | r} {repo}@{githubUser}");
	print("mwpm {folder} {packages | p} {u | i | r}");
	print("exemple: mwpm . i next-gen-exe-test@ManuelWestermeier");
}

string getGithubUrl(string arg) {
	string user;
	string repo;

	bool isRepo = true;

	for (int i = 0; i < arg.length(); i++) {
		if (arg[i] == '@')
			isRepo = false;

		else if (isRepo)
			repo += arg[i];

		else user += arg[i];
	}

	return "https://github.com/" + user + "/" + repo + ".git";
}

string getPath(string path, string arg) {
	string user;
	string repo;

	bool isRepo = true;

	for (int i = 0; i < arg.length(); i++) {
		if (arg[i] == '@')
			isRepo = false;

		else if (isRepo)
			repo += arg[i];

		else user += arg[i];
	}

	return path + "/mwpm-modules/" + user + "/" + repo + "/";
}

bool wantToInstall(int argc, char** argv) {
	bool install = (std::strcmp(argv[2], "i") == 0) || (std::strcmp(argv[2], "install") == 0);

	if (argc == 4 && install)
		return true;
	
	return false;
}

bool wantToRemove(int argc, char** argv) {
	bool remove = (std::strcmp(argv[2], "r") == 0) || (std::strcmp(argv[2], "remove") == 0);

	if (argc == 4 && remove)
		return true;

	return false;
}

bool wantToUpdate(int argc, char** argv) {
	bool update = (std::strcmp(argv[2], "u") == 0) || (std::strcmp(argv[2], "update") == 0);

	if (argc == 4 && update)
		return true;

	return false;
}

bool wantToPackage(int argc, char** argv) {
	bool package = (strcmp(argv[2], "p") == 0) || (strcmp(argv[2], "packages") == 0);
	bool isCommand = strcmp(argv[3], "u") == 0
		|| strcmp(argv[3], "i") == 0
		|| strcmp(argv[3], "r") == 0;

	if (argc == 4 && package && isCommand)
		return true;

	return false;
}

int install(string repoPath, string pathName) {
	string cmd = "git clone " + getGithubUrl(repoPath) + " " + getPath(pathName, repoPath);
	return system(cmd.c_str());
}

int remove(string repoPath, string pathName) {
	return rmDir(getPath(pathName, repoPath));
}

int update(string repoPath, string pathName) {
	return remove(repoPath, pathName) == 0 
		&& install(repoPath, pathName) == 0;
}

int installPackage(string command, string pathName) {
	string pkgFilePath = pathName + "/pkg.mwpm";

	ifstream file(pkgFilePath);

	if (!file.is_open()) {
		print("No package file (pkg.mwpm)");
		print(pkgFilePath);
		return 1;
	}

	for (string line; getline(file, line); ) {
		if (line[0] == '#') continue;
		if (line.empty()) continue;

		if (strcmp(command.c_str(), "u") == 0)
			update(line, pathName);

		else if (strcmp(command.c_str(), "i") == 0)
			install(line, pathName);
		
		else if (strcmp(command.c_str(), "r") == 0)
			remove(line, pathName);

	}

	file.close();
}

int main(int argc, char** argv)
{
	string cmdPath = argv[1];

	if (argc == 0 || argc == 1 || argc == 2)
	{
		help();
		return 1;
	}

	if (wantToInstall(argc, argv))
		return install(argv[3], cmdPath);

	if (wantToRemove(argc, argv))
		return remove(argv[3], cmdPath);

	if (wantToUpdate(argc, argv))
		return update(argv[3], cmdPath);

	if (wantToPackage(argc, argv))
		return installPackage(argv[3], cmdPath);
	
	help();
	return 1;
}