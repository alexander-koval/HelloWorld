unsigned char shaders_dither_4x4_glsl[] = {
  0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x6c, 0x75, 0x6d, 0x61, 0x28, 0x76,
  0x65, 0x63, 0x33, 0x20, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x29, 0x3b, 0x0a,
  0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x6c, 0x75, 0x6d, 0x61, 0x28, 0x76,
  0x65, 0x63, 0x34, 0x20, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x29, 0x3b, 0x0a,
  0x0a, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x64, 0x69, 0x74, 0x68, 0x65,
  0x72, 0x34, 0x78, 0x34, 0x28, 0x76, 0x65, 0x63, 0x32, 0x20, 0x70, 0x6f,
  0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2c, 0x20, 0x66, 0x6c, 0x6f, 0x61,
  0x74, 0x20, 0x62, 0x72, 0x69, 0x67, 0x68, 0x74, 0x6e, 0x65, 0x73, 0x73,
  0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x69, 0x6e, 0x74, 0x20, 0x78, 0x20,
  0x3d, 0x20, 0x69, 0x6e, 0x74, 0x28, 0x6d, 0x6f, 0x64, 0x28, 0x70, 0x6f,
  0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x78, 0x2c, 0x20, 0x34, 0x2e,
  0x30, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x69, 0x6e, 0x74, 0x20, 0x79,
  0x20, 0x3d, 0x20, 0x69, 0x6e, 0x74, 0x28, 0x6d, 0x6f, 0x64, 0x28, 0x70,
  0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x79, 0x2c, 0x20, 0x34,
  0x2e, 0x30, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x69, 0x6e, 0x74, 0x20,
  0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x20, 0x78, 0x20, 0x2b, 0x20,
  0x79, 0x20, 0x2a, 0x20, 0x34, 0x3b, 0x0a, 0x20, 0x20, 0x66, 0x6c, 0x6f,
  0x61, 0x74, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20, 0x30,
  0x2e, 0x30, 0x3b, 0x0a, 0x0a, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x78,
  0x20, 0x3c, 0x20, 0x38, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x30, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x30, 0x36, 0x32, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x31, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x35, 0x36, 0x32, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x32, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x31, 0x38, 0x37, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x33, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x36, 0x38, 0x37, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x34, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x38, 0x31, 0x32, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x35, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x33, 0x31, 0x32, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x36, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x39, 0x33, 0x37, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x37, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x34, 0x33, 0x37, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20,
  0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d,
  0x20, 0x38, 0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20,
  0x30, 0x2e, 0x32, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66,
  0x20, 0x28, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d, 0x20, 0x39,
  0x29, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20, 0x30, 0x2e,
  0x37, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28,
  0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d, 0x20, 0x31, 0x30, 0x29,
  0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20, 0x30, 0x2e, 0x31,
  0x32, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28,
  0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d, 0x20, 0x31, 0x31, 0x29,
  0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20, 0x30, 0x2e, 0x36,
  0x32, 0x35, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28,
  0x69, 0x6e, 0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d, 0x20, 0x31, 0x32, 0x29,
  0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20, 0x31, 0x2e, 0x30,
  0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x69, 0x6e,
  0x64, 0x65, 0x78, 0x20, 0x3d, 0x3d, 0x20, 0x31, 0x33, 0x29, 0x20, 0x6c,
  0x69, 0x6d, 0x69, 0x74, 0x20, 0x3d, 0x20, 0x30, 0x2e, 0x35, 0x3b, 0x0a,
  0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65,
  0x78, 0x20, 0x3d, 0x3d, 0x20, 0x31, 0x34, 0x29, 0x20, 0x6c, 0x69, 0x6d,
  0x69, 0x74, 0x20, 0x3d, 0x20, 0x30, 0x2e, 0x38, 0x37, 0x35, 0x3b, 0x0a,
  0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x69, 0x6e, 0x64, 0x65,
  0x78, 0x20, 0x3d, 0x3d, 0x20, 0x31, 0x35, 0x29, 0x20, 0x6c, 0x69, 0x6d,
  0x69, 0x74, 0x20, 0x3d, 0x20, 0x30, 0x2e, 0x33, 0x37, 0x35, 0x3b, 0x0a,
  0x20, 0x20, 0x7d, 0x0a, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72,
  0x6e, 0x20, 0x62, 0x72, 0x69, 0x67, 0x68, 0x74, 0x6e, 0x65, 0x73, 0x73,
  0x20, 0x3c, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x3f, 0x20, 0x30,
  0x2e, 0x30, 0x20, 0x3a, 0x20, 0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x7d, 0x0a,
  0x0a, 0x76, 0x65, 0x63, 0x33, 0x20, 0x64, 0x69, 0x74, 0x68, 0x65, 0x72,
  0x34, 0x78, 0x34, 0x28, 0x76, 0x65, 0x63, 0x32, 0x20, 0x70, 0x6f, 0x73,
  0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20,
  0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x72,
  0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x20,
  0x2a, 0x20, 0x64, 0x69, 0x74, 0x68, 0x65, 0x72, 0x34, 0x78, 0x34, 0x28,
  0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2c, 0x20, 0x6c, 0x75,
  0x6d, 0x61, 0x28, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x29, 0x29, 0x3b, 0x0a,
  0x7d, 0x0a, 0x0a, 0x76, 0x65, 0x63, 0x34, 0x20, 0x64, 0x69, 0x74, 0x68,
  0x65, 0x72, 0x34, 0x78, 0x34, 0x28, 0x76, 0x65, 0x63, 0x32, 0x20, 0x70,
  0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2c, 0x20, 0x76, 0x65, 0x63,
  0x34, 0x20, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x29, 0x20, 0x7b, 0x0a, 0x20,
  0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x34,
  0x28, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x2e, 0x72, 0x67, 0x62, 0x20, 0x2a,
  0x20, 0x64, 0x69, 0x74, 0x68, 0x65, 0x72, 0x34, 0x78, 0x34, 0x28, 0x70,
  0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x2c, 0x20, 0x6c, 0x75, 0x6d,
  0x61, 0x28, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x29, 0x29, 0x2c, 0x20, 0x31,
  0x2e, 0x30, 0x29, 0x3b, 0x0a, 0x7d, 0x0a
};
unsigned int shaders_dither_4x4_glsl_len = 1063;
