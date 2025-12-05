project('slang', 'c', version: '1.0.1')

slang_debug = get_option('slang_debug')
if slang_debug
    add_project_arguments('-DSLANG_DEBUG', language: 'c')
endif

osc_sources = [
    'modules/oscillators/src/oscillator.c',
    'modules/oscillators/src/sine.c',
    'modules/oscillators/src/square.c',
    'modules/oscillators/src/sawtooth.c',
    'modules/oscillators/src/triangle.c',
    'modules/oscillators/src/terrain.c',
]
osc_headers = [
    'modules/oscillators/include/oscillator.h',
    'modules/oscillators/include/sine.h',
    'modules/oscillators/include/square.h',
    'modules/oscillators/include/sawtooth.h',
    'modules/oscillators/include/triangle.h',
    'modules/oscillators/include/terrain.h',
    'modules/oscillators/include/oscillator_types.h',
]
data_sources = [
    'modules/data/src/binaryData.c',
]
data_headers = [
    'modules/data/include/binaryData.h',
]
step_sources = [
    'modules/stepsequencer/src/stepsequencer.c',
]
step_headers = [
    'modules/stepsequencer/include/stepsequencer.h',
    'modules/stepsequencer/include/stepsequencer_types.h',
]
sample_source_sources = [   
    'modules/sample-source/src/sample_source.c',
]
sample_source_headers = [
    'modules/sample-source/include/sample_source.h',
]
filter_sources = [
    'modules/filters/src/lowpassfilter.c',
]
filter_headers = [
    'modules/filters/include/lowpassfilter.h',
    'modules/filters/include/filter_types.h',
]

slang_modules = shared_library(
  'slang_modules',
  data_sources + data_headers +
  osc_sources + osc_headers +
  step_sources + step_headers +
  sample_source_sources + sample_source_headers +
  filter_sources + filter_headers,
  include_directories: include_directories('modules/'),
  dependencies: [],
  link_args: ['-lm'], 
  install: true
)