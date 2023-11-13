#ifndef MTM0_ORDERS_H
#define MTM0_ORDERS_H
#include "set.h"

typedef struct order_t* Order;

/**
 * orderCopy: Copies an existing order.
 *
 * @param element - Generic pointer to a element.
 * @return
 *     NULL -  if element are Null, or in the case of allocation error.
 *     Copy order - if copies the order successfully.
 */
void* orderCopy(void* order);

/**
 * orderFree: free order.
 *
 * @param element - Generic pointer to the free.
 */
void orderFree(void* element);

/**
 * orderCompare: compares two orders.
 *
 * @param first_element - pointer to the first order.
 * @param second_element - pointer to the second order.

 * @return
 *     0 -  if one of the orders doesn't exist.
 *     >0 - if the first order was places before the seconds order.
 *     <0 - if the first order was places after the seconds order.
 */
int orderCompare(void* first_element, void* second_element);

/**
 * orderCreat: Creat new order.
 *
 * @param orderId - an id of a product.
 * @return
 *     NULL -  in the case of allocation error.
 *     new order - if places the order successfully.
 */
 Order orderCreat(unsigned int orderId);

/**
 * getOrderID: Gets the ID of a given order.
 *
 * @param product - a given order.

 * @return
 *     ID of order - if order exists.
 */
unsigned int getOrderID(Order order);

/**
 * getOrderProducts: Gets the products of a given order.
 *
 * @param product - a given order.

 * @return
 *     Null - if product is Null.
 *     products of order - if order exists.
 */
Set getOrderProducts(Order order);

/**
 * setOrderID: Sets the ID of a given order.
 *
 * @param product - a given order.
 */
void setOrderID(Order order, unsigned int orderId);

/**
 * getOrderProfits: Gets how much profit will be gained from the order.
 *
 * @param product - a given product.

 * @return
 *     Null - if product is Null.
 *     total profit of order - if order exists.
 */
double getOrderProfits(Order order);

/**
 * removeOrderProductByID: Removes an order by id.
 *
 * @param order - a given product.
 * @param productId - id of order
 */
void removeOrderProductByID(Order order, unsigned int productId);

#endif //MTM0_ORDERS_H
