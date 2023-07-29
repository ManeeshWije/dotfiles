from PIL import Image
import numpy as np

img = Image.open("./Gray.jpg")

imgArr = np.array(img)
# print(imgArr)
#
# imgArr = 255 - imgArr
#
# inverse = Image.fromarray(imgArr)
#
# inverse.save('inverseGray.jpg')

# --------------------------------------------------------

# IMin = 1000
# for i in range(imgArr.shape[0]):
#     for j in range(imgArr.shape[1]):
#         if IMin > imgArr[i][j]:
#             IMin = imgArr[i][j]
#
# IMax = -1
# for i in range(imgArr.shape[0]):
#     for j in range(imgArr.shape[1]):
#         if IMax < imgArr[i][j]:
#             IMax = imgArr[i][j]
#
# pixelSum = 0
# for i in range(imgArr.shape[0]):
#     for j in range(imgArr.shape[1]):
#         pixelSum += imgArr[i][j]
# avg = pixelSum / (imgArr.shape[0] * imgArr.shape[1])
# print(avg)

# --------------------------------------------------------

# T = 128
# newImage = np.copy(imgArr)
# for i in range(imgArr.shape[0]):
#     for j in range(imgArr.shape[1]):
#         if imgArr[i][j] <= T:
#             newImage[i][j] = 0
#         else:
#             newImage[i][j] = 255

# new = Image.fromarray(newImage)
# new.save('newImage.jpg')

# --------------------------------------------------------

# absDiffImage = np.copy(imgArr)
# for i in range(imgArr.shape[0]):
#     for j in range(imgArr.shape[1]):
#         if imgArr[i][j] > newImage[i][j]:
#             absDiffImage[i][j] = imgArr[i][j] - newImage[i][j]
#         else:
#             absDiffImage[i][j] = newImage[i][j] - imgArr[i][j]
# new = Image.fromarray(absDiffImage)
# new.save('absImage.jpg')


