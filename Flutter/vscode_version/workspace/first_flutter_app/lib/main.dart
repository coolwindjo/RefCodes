import 'dart:io';

import 'package:image_picker/image_picker.dart';
import 'package:flutter/material.dart';

void main() => runApp(ImagePickerApp());

class ImagePickerApp extends StatefulWidget {
  @override
  _ImagePickerAppState createState() => _ImagePickerAppState();
  
}

class _ImagePickerAppState extends State<ImagePickerApp> {
  File _image;

  Future getImage() async{
    var image = await ImagePicker.pickImage(source: ImageSource.camera);
    setState(() {
     _image = image; 
    });
  }

  @override
  Widget build(BuildContext context) {
    return new MaterialApp(title: 'Image Picker',
    home: new Scaffold(
      appBar: new AppBar(title: new Text('Image Picker'),
      ),
      body: new Center(child: _image == null? new Text('No image selected'):new Image.file(_image),
      ),
      floatingActionButton: new FloatingActionButton(onPressed: getImage,tooltip: 'Pick Image', child: new Icon(Icons.camera),
      ),
    ),
    theme: ThemeData(
      primarySwatch: Colors.red,
      fontFamily: 'Roboto',
    ),
    );
  }
}
