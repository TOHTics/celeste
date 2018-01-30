# Database Configuration

The Celeste server assumes that there exists a DB connection to a MySQL server with a schema named `Celeste`. This guide is written assuming the OS is [Ubuntu Server 16.04 LTS](https://www.ubuntu.com/download/server) but should work on most Linux, and probably Unix, distros.

# Table of Contents

1. [Add the MySQL APT repository](#add-the-mysql-apt-repository)
2. [Install the server](#install-the-server)
3. [Start and set to restart on reboot](#start-and-set-to-restart-on-reboot)
4. [Build the Schema](#build-the-schema)


# MySQL Installation

The installation for MySQL server must be done using `apt-get` and the packages must be taken from the [MySQL APT Repository](https://dev.mysql.com/doc/mysql-apt-repo-quick-guide/en/). We will now give the details of the MySQL installation. We recommend creating a temporary directory to store all the files in. Also, the [APT repo versions](https://dev.mysql.com/downloads/repo/apt/) may change so be sure to check for the latest one. In this guide we utilize version `0.8.9-1_all`. So let's get right to it.


## 1. Add the MySQL APT repository

Firstly we must add the MySQL APT repo:

```
wget https://dev.mysql.com/get/mysql-apt-config_0.8.9-1_all.deb
sudo dpkg -i mysql-apt-config_0.8.9-1_all.deb
```

Please select the following options for:

```
MySQL Server & Cluster (mysql-5.7)
MySQL Tools & Connectors (Enabled)
MySQL Preview Packages (Disabled)                                                                                      
```
And select `OK`.

## 2. Install the server

Next we execute to update the list of packages available:

```
sudo apt-get update
```

Install `mysql-server` by specifying a password during installation:

```
sudo apt-get install mysql-server
```

## 3. Start and set to restart on reboot
Start `mysql-server`:

```
sudo service mysql start
```

Set to restart the server on reboot:

```
sudo /usr/sbin/update-rc.d mysql defaults
```


## 4. Build the Schema

Celeste Server requires some tables to be on the DB. For this, we provide the `BUILD_DB.sql` script. To execute this script log in to the MySQL client and enter your password:

```
cd dir_to_script/
mysql -u USER -p
```

And type:

```
mysql> source BUILD_DB.sql
```

This will create a schema named `celestesensordata` along with its associated tables.