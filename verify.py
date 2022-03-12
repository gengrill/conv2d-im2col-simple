import fileinput
import numpy as np
import scipy.signal
np.set_printoptions(edgeitems=10,linewidth=180)
input_strings = ['', '', '']
input_index   = 0
for line in fileinput.input():
    if line == '\n':
        input_index += 1
        continue
    input_strings[input_index] += line
image  = eval('np.array(['+input_strings[0]+'])')
filter = eval('np.array(['+input_strings[1]+'])')
result = eval('np.array(['+input_strings[2]+'])')
correct = scipy.signal.convolve2d(image, filter, mode='same')
np.testing.assert_array_almost_equal(result, correct, decimal=5)
print('Verified successfully.')
