mass-delivery
=============

The mass-delivery extension allows a user to send message to a list of users.

Note: This extension should be checked out in the folder named "huggle" in your huggle3-qt-lx repo

How to build
=============

Prepare a directory for build, in this example it's /tmp/huggle

```
cd /tmp/huggle
git clone http://github.com/huggle/mass-delivery
git clone http://github.com/huggle/huggle3-qt-lx
# build core
cd huggle3-qt-lx/huggle
./configure
make
cd -
cd mass-delivery-md
qmake
make
# copy the plugin to extensions dir
cp libMassDelivery.so ../..
cd -
cd huggle3-qt-lx/huggle
mkdir extensions
mv ../../libMassDelivery.so extensions
```

Now you should have the mass-delivery extension installed in Huggle
