class CreateConfigs < ActiveRecord::Migration[5.1]
  def change
    create_table :configs do |t|
        t.string :key
        t.string :value
        t.timestamps null: false
    end
  end
end
