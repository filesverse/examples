project('example', 'cpp', version: '1.0', default_options: ['cpp_std=c++17'])

filerix = dependency('filerix', required: true)

src = files(
  'src/example.cc',
)

executable('example', src, dependencies: filerix)