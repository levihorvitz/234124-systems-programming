#ifndef MTM0_PRODUCT_H
#define MTM0_PRODUCT_H
#include "stdbool.h"
#include "Matamikya.h"

typedef struct product_t* Product;

/**
 * productCreat: creat of product.
 *
 * @param productId - new product productId. Must be non-negative, and unique.
 * @param name - name of the product, e.g. "apple". Must be non-empty.
 * @param amount - the initial amount of the product when added to the warehouse.
 * @param amountType - defines what are valid amounts for this product.
 * @param productData - pointer to product's additional element
 * @param copyData - function pointer to be used for copying product's additional
 *      element.
 * @param freeData - function pointer to be used for free product element.
 * @param getProductPrice - function pointer to be used for getting the price of some
 *      product.
 * @return
 *     NULL -  if name/productData/copyData/freeData/newProduct are Null.
 *     new product - if the creation is successfull.
 */
Product productCreat(const char* name,
					 unsigned int productId,
					 double amount,
					 MatamikyaAmountType amountType,
					 MtmProductData productData,
					 MtmCopyData copyData,
					 MtmFreeData freeData,
					 MtmGetProductPrice getProductPrice);

/**
 * productCopy: copies product.
 *
 * @param element - Generic pointer to a product.
 * @return
 *     NULL -  if element are Null.
 *     copy product - if copies product successfully.
 */
void* productCopy(void* element);

/**
 * productFree: frees product.
 *
 * @param element - Generic pointer to a element.
 */
void productFree(void* element);

/**
 * productCompare: compares products.
 *
 * @param first_product - pointer to the first product.
 * @param second_product - pointer to the second product.

 * @return
 *     0 -  if the first and second product are the same product.
 *     1 - if the first product comes before the second product.
 *     -1 - if the first product comes after the second product.

 */
int productCompare(void* first_product, void* second_product);

/**
 * compareProductID: checkes if the given ID matches the given product.
 *
 * @param product - a given product.
 * @param id - a given ID.

 * @return
 *     true -  if the given ID is match the ID of the given product.
 *     false - if the given ID doesn't match the ID of the given product.
 */
bool compareProductID(Product product, unsigned int id);

/**
 * getProductName: Gets the name of a given product
 *
 * @param product - a given product.

 * @return
 *     Null - if product is Null.
 *     name of product - if product exists.
 */
char* getProductName(Product product);

/**
 * getProductID: Gets the ID of a given product
 *
 * @param product - a given product.

 * @return
 *     0 - if product is Null.
 *     product Id - if product exists.
 */
unsigned int getProductID(Product product);

/**
 * getProductAmountType: Checks the amount type of the product.
 *
 * @param product - a given product.

 * @return
 *     -1 - if product is Null.
 *     amount type - if product exists.
 */
MatamikyaAmountType getProductAmountType(Product product);

/**
 * getProductAmount: Gets the amount of the product.
 *
 * @param product - a given product.

 * @return
 *     0 - if product is Null.
 *     amount of product - if product exists.
 */
double getProductAmount(Product product);

/**
 * getProductTotalPrice: Gets the total price of the product.
 *
 * @param product - a given product.

 * @return
 *     0 - if product is Null.
 *     total price - if product exists.
 */
double getProductTotalPrice(Product product);

/**
 * getProductPriceOneUnit: Gets the price of one unit of the product.
 *
 * @param product - a given product.

 * @return
 *     0 - if product is Null.
 *     price of product - if product exists.
 */
double getProductPriceOneUnit(Product product);

/**
 * getProductTotalInCome: Gets how much profit the product made.
 *
 * @param product - a given product.

 * @return
 *     0 - if product is Null.
 *     the total in come of the product - if product exists.
 */
double getProductTotalInCome(Product product);

/**
 * setProductAmount: set the amount of the product.
 *
 * @param product - a given product.
 * @param amount - amount of the product.
 */
void setProductAmount(Product product, double amount);

/**
 * addProductAmount: add amount products.
 *
 * @param product - a given product.
 * @param amount - the new stock amount that has been added to the product.
 */
void addProductAmount(Product product, double amount);

/**
 * setProductTotalInCome: set the total in come of the product.
 *
 * @param product - a given product.
 * @param amount - the amount of the products.
 */
void setProductTotalInCome(Product product, double amount);

#endif //MTM0_PRODUCT_H
