# Integration test for Buzzline
require_relative '../app.rb'
# Ensure Rack::Test is loaded
require 'rack/test'

# Ensure Sinatra is in the correct mode
set :environment, :test

# And RSpec knows we're using Sinatra
def app
	Sinatra::Application
end

# Check the tutorial functions
describe "Basic tutorial" do
	include Rack::Test::Methods
	it "redirects to /hello"
		get '/'
		last_response.status.should == 301
	end
	it "redirects to /hello/world"
		get '/hello'
		last_response.status.should == 301
	end
	it "says 'Hello, World'"
		get '/hello/world'
		last_response.should be_ok
	end
end
