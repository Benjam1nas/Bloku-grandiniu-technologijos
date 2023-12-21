const Marketplace = artifacts.require('./Marketplace.sol')

require('chai')
	.use(require('chai-as-promised'))
	.should()

contract('Marketplace', ([deployer, seller, buyer]) => {
	let marketplace

	before(async () => {
		marketplace = await Marketplace.deployed()
	})

	describe('deployment', async() => {
		it('deploys successfully', async () => {
			const address = await marketplace.address
			assert.notEqual(address, 0x0)
			assert.notEqual(address, '')
			assert.notEqual(address, null)
			assert.notEqual(address, undefined)
		})

		it('has a name', async () => {
			const name = await marketplace.name()
			assert.equal(name, 'Online parduotuve')
		})
	})

	describe('products', async() => {
		let result, productCount

		before(async () => {
			result = await marketplace.createProduct('Iphone 14 Pro', web3.utils.toWei('0.5', 'Ether'), { from: seller })
			productCount = await marketplace.productCount()
		})

		it('creates products', async () => {
			//Success
			assert.equal(productCount, 1)
			const event = result.logs[0].args
			assert.equal(event.id.toNumber(), productCount.toNumber(), 'id is correct')
			assert.equal(event.name, 'Iphone 14 Pro', 'name is correct')
			assert.equal(event.price, '500000000000000000', 'price is correct')
			assert.equal(event.owner, seller, 'owner is correct')
			assert.equal(event.purchased, false, 'not purchased')

			//Fail: Product must have a name
			await await marketplace.createProduct('', web3.utils.toWei('0.5', 'Ether'), { from: seller }).should.be.rejected;
			//Fail: Product must have a price
			await await marketplace.createProduct('Iphone 14 Pro', 0, { from: seller }).should.be.rejected;
		})

		it('lists products', async () => {
			const product = await marketplace.products(productCount)
			assert.equal(product.id.toNumber(), productCount.toNumber(), 'id is correct')
			assert.equal(product.name, 'Iphone 14 Pro', 'name is correct')
			assert.equal(product.price, '500000000000000000', 'price is correct')
			assert.equal(product.owner, seller, 'owner is correct')
			assert.equal(product.purchased, false, 'not purchased')
		})

		it('sells products', async () => {
			// Track seller balance before purchase
			let oldSellerBalance
			oldSellerBalance = await web3.eth.getBalance(seller)
			oldSellerBalance = new web3.utils.BN(oldSellerBalance)

			// Success: Buyer makes purchase
			result = await marketplace.purchasedProduct(productCount, { from: buyer, value: web3.utils.toWei('0.5', 'Ether')})

			//Check logs
			const event = result.logs[0].args
			assert.equal(event.id.toNumber(), productCount.toNumber(), 'id is correct')
			assert.equal(event.name, 'Iphone 14 Pro', 'name is correct')
			assert.equal(event.price, '500000000000000000', 'price is correct')
			assert.equal(event.owner, buyer, 'owner is correct')
			assert.equal(event.purchased, true, 'not purchased')

			//Seller recieves funds
			let newSellerBalance
			newSellerBalance = await web3.eth.getBalance(seller)
			newSellerBalance = new web3.utils.BN(newSellerBalance)

			let price
			price = web3.utils.toWei('0.5', 'Ether')
			price = new web3.utils.BN(price)

			const expectedBalance = oldSellerBalance.add(price)

			assert.equal(newSellerBalance.toString(), expectedBalance.toString())

			// Fail: Trying to buy a product that does not exist
			await marketplace.purchasedProduct(99, { from: buyer, value: web3.utils.toWei('0.5', 'Ether')}).should.be.rejected

			// Fail: Trying to buy a product without enough balance
			await marketplace.purchasedProduct(productCount, { from: buyer, value: web3.utils.toWei('0.25', 'Ether')}).should.be.rejected

			// Fail: Trying to buy the same product twice
			await marketplace.purchasedProduct(productCount, { from: deployer, value: web3.utils.toWei('0.5', 'Ether')}).should.be.rejected

			// Fail: Buyer tries to buy from buyer
			await marketplace.purchasedProduct(productCount, { from: seller, value: web3.utils.toWei('0.5', 'Ether')}).should.be.rejected //Different line
		})

	})
})