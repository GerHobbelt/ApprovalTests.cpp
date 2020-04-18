from __future__ import annotations

import configparser
import os
from typing import Dict, cast


class Version:
    def __init__(self, major: int, minor: int, patch: int) -> None:
        self.major = major
        self.minor = minor
        self.patch = patch

    @staticmethod
    def _version_file_path(directory: str) -> str:
        return os.path.join(directory, 'version.ini')

    @staticmethod
    def read(directory: str) -> Version:
        config = configparser.ConfigParser()
        config.read(Version._version_file_path(directory))
        version = cast(Dict[str, str], config['VERSION'])
        return Version.from_map(version)

    def write(self, directory: str) -> None:
        config = configparser.ConfigParser()
        config['VERSION'] = self.as_map()

        with open(Version._version_file_path(directory), 'w') as configfile:
            config.write(configfile)

    def update_major(self) -> Version:
        return Version(self.major + 1, 0, 0)

    def update_minor(self) -> Version:
        return Version(self.major, self.minor + 1, 0)

    def update_patch(self) -> Version:
        return Version(self.major, self.minor, self.patch + 1)

    def clone(self) -> Version:
        return Version(self.major, self.minor, self.patch)

    def as_map(self) -> Dict[str, str]:
        return {"major": str(self.major), "minor": str(self.minor), "patch": str(self.patch)}

    @staticmethod
    def from_map(version: Dict[str, str]) -> Version:
        return Version(
            int(version['major']),
            int(version['minor']),
            int(version['patch']))

    def get_version_text(self, prefix:str = 'v.') -> str:
        return F"{prefix}{self.major}.{self.minor}.{self.patch}"

    def get_version_text_without_v(self) -> str:
        return self.get_version_text('')


def get_version_without_v(version_string: str) -> str:
    return version_string.replace("v.", "")


def update_major(version: Dict[str, str]) -> Dict[str, str]:
    return Version.from_map(version).update_major().as_map()


def update_minor(version: Dict[str, str]) -> Dict[str, str]:
    return Version.from_map(version).update_minor().as_map()


def update_patch(version: Dict[str, str]) -> Dict[str, str]:
    return Version.from_map(version).update_patch().as_map()


def no_version_change(version: Dict[str, str]) -> Dict[str, str]:
    # This is useful if a deploy failed part-way through, and we don't want to increment the version number
    return Version.from_map(version).clone().as_map()
