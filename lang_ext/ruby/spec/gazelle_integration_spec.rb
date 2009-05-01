require File.dirname(__FILE__) + "/spec_helper"

module Gazelle
  describe Parser do
    describe "a new parser given a stream" do
      before do
        File.stub!(:read).and_return "some text"
      end

      it "should create a new Gazelle::Parser" do
        Parser.new("a/file").should be_a_kind_of(Gazelle::Parser)
      end
    end

    describe "parse" do
      before do
        @parser = Parser.new(File.dirname(__FILE__) + "/hello.gzc")
      end

      it "should be true if it can parse the input" do
        @parser.parse?("(5)").should be_true
      end

      it "should be false if it cannot parse the input" do
        @parser.parse?("(()").should be_false
      end
    end
  end
end
