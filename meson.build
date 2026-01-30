project('slang', 'c', version: '1.0.1')

# Enable POSIX functions like getline()
if host_machine.system() == 'darwin'
    add_project_arguments('-D_DARWIN_C_SOURCE', language: 'c')
else
    add_project_arguments('-D_GNU_SOURCE', language: 'c')
endif

slang_debug = get_option('slang_debug')
if slang_debug
    add_project_arguments('-DSLANG_DEBUG', language: 'c')
endif

slangonic = get_option('slangonic')
if slangonic
    add_project_arguments('-DSLANGONIC', language: 'c')
endif

osc_sources = [
    'modules/oscillators/src/oscillator.c',
    'modules/oscillators/src/sine.c',
    'modules/oscillators/src/square.c',
    'modules/oscillators/src/sawtooth.c',
    'modules/oscillators/src/triangle.c',
    'modules/oscillators/src/terrain.c',
    'modules/oscillators/src/wavetable.c',
]
osc_headers = [
    'modules/oscillators/include/oscillator.h',
    'modules/oscillators/include/sine.h',
    'modules/oscillators/include/square.h',
    'modules/oscillators/include/sawtooth.h',
    'modules/oscillators/include/triangle.h',
    'modules/oscillators/include/terrain.h',
    'modules/oscillators/include/wavetable.h',
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
envelope_sources = [
    'modules/envelope/src/envelope.c',
    'modules/envelope/src/linenvelope.c',
]
envelope_headers = [
    'modules/envelope/include/envelope_types.h',
    'modules/envelope/include/envelope.h',
    'modules/envelope/include/linenvelope.h',
]

core_headers = [
    'core/include/buffer_core.h',
    'core/include/core_types.h',
    'core/include/function.h',
    'core/include/interpreter.h',
    'core/include/parser.h',
    'core/include/rack.h',
    'core/include/tokenizer.h',
    'core/include/tools.h',
    'core/include/variable.h',
]
core_sources = [
    'core/src/buffer_core.c',
    'core/src/function.c',
    'core/src/interpreter.c',
    'core/src/parser.c',
    'core/src/rack.c',
    'core/src/tokenizer.c',
    'core/src/tools.c',
]

slang_lib = shared_library(
  'slang',
  core_sources + core_headers +
  data_sources + data_headers +
  osc_sources + osc_headers +
  step_sources + step_headers +
  sample_source_sources + sample_source_headers +
  filter_sources + filter_headers +
  envelope_sources + envelope_headers,
  include_directories: include_directories('core/', 'modules/'),
  dependencies: [],
  link_args: ['-lm'],
  install: true
)

tester_exe = executable(
  'tester',
  'tester.c',
  include_directories: include_directories('core/', 'modules/'),
  link_with: slang_lib,
  link_args: ['-lm'], 
)

slang_exe = executable(
    'slang',
    'slang.c',
    link_with: slang_lib,
    link_args: ['-lm']
)
